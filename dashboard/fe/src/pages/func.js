import React from 'react';
import { connect } from 'react-redux';
import { PageHeader, Drawer } from 'antd';
import FuncList from '../components/func_list';
import NamespaceSelecter from '../components/namespace_selector';
import FuncCreateButton from '../components/func_create_button';

class Page extends React.PureComponent {

    state = { drawerVisible: false }

    onClose = () => { this.setState({ drawerVisible: false }); }

    render() {
        return (
            <div>
                <PageHeader
                    title="函数服务"
                    extra={[
                        <NamespaceSelecter key="select" />,
                        <FuncCreateButton key="new" />
                    ]} />

                <FuncList />

                <Drawer
                    visible={this.state.drawerVisible}
                    layout='vertical'
                    onClose={this.onClose}
                    width={720}>

                </Drawer>
            </div>
        );
    }
}

export default connect()(Page);
