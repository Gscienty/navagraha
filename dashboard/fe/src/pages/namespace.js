import React from 'react';
import { connect } from 'react-redux';
import { PageHeader, Row, Col } from 'antd';
import NamespaceList from '../components/namespace_list';
import NamespaceAddButton from '../components/namespace_add';

class Page extends React.PureComponent {

    constructor(props) {
        super(props);
    }

    render() {
        return (
            <div>
                <PageHeader title="命名空间" extra={[<NamespaceAddButton />]}>
                </PageHeader>

                <NamespaceList />
            </div>
        );
    }
}

export default connect()(Page);
