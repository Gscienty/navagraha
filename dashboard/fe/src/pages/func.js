import React from 'react';
import { connect } from 'react-redux';
import { PageHeader, Drawer, Button } from 'antd';
import FuncList from '../components/func_list';
import NamespaceSelecter from '../components/namespace_selector.js';

class Page extends React.PureComponent {

    state = { drawerVisible: false }

    onClose = () => { this.setState({ drawerVisible: false }); }

    render() {
        return (
            <div>
                <PageHeader
                    title="函数服务"
                    extra={[
                        <span key="selector"><NamespaceSelecter /></span>,

                        <Button key="new" type="primary" onClick={() => this.setState({drawerVisible: true})}>创建</Button>,
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
