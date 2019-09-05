import React from 'react';
import { connect } from 'react-redux';
import { PageHeader } from 'antd';
import NodeList from '../components/node_list';

class Page extends React.PureComponent {

    render() {
        return (
            <div>
                <PageHeader title="主机资产" />

                <NodeList />
            </div>
        );
    }
}

export default connect()(Page);
